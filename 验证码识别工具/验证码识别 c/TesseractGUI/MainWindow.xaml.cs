using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using System.Text.RegularExpressions;
using System.Diagnostics;
using System.Windows.Forms;
using System.Net;
using System.Threading;

namespace TesseractGUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        #region 全局变量
        private string __OutputFileName = string.Empty;
        private WebClient client = new WebClient();
        #endregion

        #region 系统函数
        public MainWindow()
        {
            InitializeComponent();
        }
        #endregion

        #region 用户函数
        private bool fn数据验证()
        {
            if ((bool)this.rbtn本地图片.IsChecked)
            {
                if (!File.Exists(this.txt本地图片.Text))
                {
                    this.labMsg.Content = "本地图片不存在，请重新选择。";
                    this.txt本地图片.Focus();
                    return true;
                }
            }

            if ((bool)this.rbtn网络图片.IsChecked)
            {
                Regex reg = new Regex(@"^https?://([\w-]+\.)+[\w-]+(/[\w- ./?%&=]*)?$");
                if (!reg.IsMatch(this.txt网络图片.Text))
                {
                    this.labMsg.Content = "网络图片路径错误，请在浏览器中测试能否打开该图片。";
                    this.txt网络图片.Focus();
                    return true;
                }
            }

            if (!Directory.Exists(this.txt输出目录.Text))
            {
                this.labMsg.Content = "输出目录不存在，请重新选择。";
                this.txt输出目录.Focus();
                return true;
            }

            return false;
        }

        private void fnStartDownload(string v_strImgPath, string v_strOutputDir, out string v_strTmpPath)
        {
            int n = v_strImgPath.LastIndexOf('/');
            string URLAddress = v_strImgPath.Substring(0, n);
            string fileName = v_strImgPath.Substring(n + 1, v_strImgPath.Length - n - 1);
            this.__OutputFileName = v_strOutputDir + "\\" + fileName.Substring(0, fileName.LastIndexOf("."));

            if (!Directory.Exists(System.Configuration.ConfigurationManager.AppSettings["tmpPath"]))
            {
                Directory.CreateDirectory(System.Configuration.ConfigurationManager.AppSettings["tmpPath"]);
            }

            string Dir = System.Configuration.ConfigurationManager.AppSettings["tmpPath"];
            v_strTmpPath = Dir + "\\" + fileName;

            WebRequest myre = WebRequest.Create(URLAddress);
            client.DownloadFile(v_strImgPath, v_strTmpPath);


            //Stream str = client.OpenRead(v_strImgPath);
            //StreamReader reader = new StreamReader(str);
            //byte[] mbyte = new byte[Int32.Parse(System.Configuration.ConfigurationManager.AppSettings["MaxDownloadImgLength"])];
            //int allmybyte = (int)mbyte.Length;
            //int startmbyte = 0;
            //while (allmybyte > 0)
            //{
            //    int m = str.Read(mbyte, startmbyte, allmybyte);
            //    if (m == 0)
            //    {
            //        break;
            //    }

            //    startmbyte += m;
            //    allmybyte -= m;
            //}

            //FileStream fstr = new FileStream(v_strTmpPath, FileMode.Create, FileAccess.Write);
            //fstr.Write(mbyte, 0, startmbyte);
            //str.Close();
            //fstr.Close();
        }

        private void fnOCR(string v_strTesseractPath, string v_strSourceImgPath, string v_strOutputPath, string v_strLangPath)
        {
            using (Process process = new System.Diagnostics.Process())
            {
                process.StartInfo.FileName = v_strTesseractPath;
                process.StartInfo.Arguments = v_strSourceImgPath + " " + v_strOutputPath + " -l " + v_strLangPath;
                process.StartInfo.UseShellExecute = false;
                process.StartInfo.CreateNoWindow = true;
                process.StartInfo.RedirectStandardOutput = true;
                process.Start();
                process.WaitForExit();
            }
        }
        #endregion

        #region 系统事件
        private void btn浏览_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Title = "请选择一个本地图片";
            ofd.Multiselect = false;
            ofd.Filter = "支持图片格式(*.jpg,*.jpeg,*.gif,*.bmp,*.png)|*.jpg;*.jpeg;*.gif;*.bmp;*.png";

            if (ofd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                this.txt本地图片.Text = ofd.FileName;
                this.img图片.Source = new BitmapImage(new Uri(ofd.FileName, UriKind.RelativeOrAbsolute));

                this.labMsg.Content = "本地图片已成功加载。";
            }
        }

        private void rbtn本地图片_Checked(object sender, RoutedEventArgs e)
        {
            if (this.IsInitialized)
            {
                if ((bool)this.rbtn本地图片.IsChecked)
                {
                    this.txt本地图片.Text = string.Empty;
                    this.txt本地图片.IsEnabled = true;
                    this.btn浏览.IsEnabled = true;
                    this.txt本地图片.Focus();

                    this.txt网络图片.Text = "http://";
                    this.txt网络图片.IsEnabled = false;

                    this.img图片.Source = null;
                }
            }
        }

        private void rbtn网络图片_Checked(object sender, RoutedEventArgs e)
        {
            if (this.IsInitialized)
            {
                if ((bool)this.rbtn网络图片.IsChecked)
                {
                    this.txt本地图片.Text = string.Empty;
                    this.txt本地图片.IsEnabled = false;
                    this.btn浏览.IsEnabled = false;

                    this.txt网络图片.Text = "http://";
                    this.txt网络图片.IsEnabled = true;

                    this.img图片.Source = null;
                }
            }
        }

        private void txt网络图片_TextChanged(object sender, TextChangedEventArgs e)
        {
            Regex reg = new Regex(@"^https?://([\w-]+\.)+[\w-]+(/[\w- ./?%&=]*)?$");
            if (reg.IsMatch(this.txt网络图片.Text))
            {
                this.img图片.Source = new BitmapImage(new Uri(this.txt网络图片.Text, UriKind.RelativeOrAbsolute));

                this.labMsg.Content = "网络图片已成功加载。";
            }
        }

        private void btn输出浏览_Click(object sender, RoutedEventArgs e)
        {
            FolderBrowserDialog fbd = new FolderBrowserDialog();
            fbd.Description = "请选择一个输出目录";
            if (fbd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                this.txt输出目录.Text = fbd.SelectedPath;
            }
        }

        private void btn清空_Click(object sender, RoutedEventArgs e)
        {
            this.txtOCRed.Text = string.Empty;
            this.txtOCRed.Focus();
        }

        private void btnOCR_Click(object sender, RoutedEventArgs e)
        {
            if (this.fn数据验证())
            {
                return;
            }

            try
            {
                DirectoryInfo dir = new DirectoryInfo(this.txt输出目录.Text);

                if ((bool)this.rbtn本地图片.IsChecked)
                {
                    FileInfo file = new FileInfo(this.txt本地图片.Text);
                    string name = file.Name.Substring(0, file.Name.LastIndexOf("."));
                    this.__OutputFileName = dir.FullName + @"\" + name;

                    this.fnOCR(System.Configuration.ConfigurationManager.AppSettings["TesseractPath"]
                        , this.txt本地图片.Text, this.__OutputFileName
                        , System.Configuration.ConfigurationManager.AppSettings["LangPath"]);
                }
                else if ((bool)this.rbtn网络图片.IsChecked)
                {
                    string TmpPath = string.Empty;
                    this.fnStartDownload(this.txt网络图片.Text, dir.FullName, out TmpPath);
                    this.fnOCR(System.Configuration.ConfigurationManager.AppSettings["TesseractPath"]
                        , TmpPath, this.__OutputFileName
                        , System.Configuration.ConfigurationManager.AppSettings["LangPath"]);
                }

                FileStream fs = new FileStream(this.__OutputFileName + ".txt", FileMode.Open, FileAccess.Read);
                StreamReader sr = new StreamReader(fs);
                this.txtOCRed.Text = sr.ReadToEnd();

                sr.Close();
                this.labMsg.Content = "OCR成功。";
            }
            catch
            {
                this.labMsg.Content = "OCR失败。";
            }
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            DirectoryInfo dir = new DirectoryInfo("tmp");
            foreach (FileInfo file in dir.GetFiles())
            {
                file.Delete();
            }
        }
        #endregion
    }
}
