using System.ComponentModel;

namespace WinFormsApp2
{
    public partial class Form1 : Form
    {
        private bool isCalculating;
        private Thread calculationThread;
        public Form1()
        {
            InitializeComponent();
            John.DoWork += Worker_work;
            John.ProgressChanged += Worker_ProgressChanged;
            John.RunWorkerCompleted += Worker_RunWorkerCompleted;
            this.DoubleBuffered = true;

        }
        private void button1_Click(object sender, EventArgs e)
        {
            smoothBar1.Value = 0;
            if (!John.IsBusy)
            {
                John.RunWorkerAsync();
            }

            smoothBarThread.Value = 0;

            if (!isCalculating)
            {
                isCalculating = true;
                calculationThread = new Thread(Thread_Work);
                calculationThread.Start();
            }

        }

        private void Worker_work(object sender, DoWorkEventArgs e)
        {
            int totalNumbers = 1000;
            int primeCount = 0;
            smoothBar1.Max = totalNumbers;
            smoothBar1.Min = 0;

            for (int i = 2; i <= totalNumbers; i++)
            {
                if (longIsPrime(i)) primeCount++;
                John.ReportProgress(i);
                Thread.Sleep(5);
            }


        }

        private void Worker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            smoothBar1.Value = e.ProgressPercentage;
        }

        private void Worker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (e.Error != null)
            {
                MessageBox.Show("Error occurred: " + e.Error.Message);
            }
        }



        private void Thread_Work()
        {
            int totalNumbers = 1000;
            int primeCount = 0;
            smoothBarThread.Max = totalNumbers;
            smoothBarThread.Min = 0;
            for (int i = 2; i <= totalNumbers; i++)
            {
                if (longIsPrime(i))
                {
                    primeCount++;
                }

                
                ThreadUpdateProgressBar(i);

                Thread.Sleep(5);
            }

            isCalculating = false;
            MessageBox.Show($"Found {primeCount} prime numbers.");
        }

        private void ThreadUpdateProgressBar(int value)
        {
            if (smoothBarThread.InvokeRequired)
            {
                smoothBarThread.BeginInvoke((Action<int>)ThreadUpdateProgressBar, value);
            }
            else
            {
                smoothBarThread.Value = value;
            }
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {

        }
        private bool longIsPrime(int a)
        {
            if (a <= 1) return false;

            for (int i = 2; i < a; i++)
            {
                if (a % i == 0) return false;
            }
            return true;
        }

        private void smoothProgressBar2_Click(object sender, EventArgs e)
        {

        }
    }
}
