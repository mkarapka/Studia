namespace WinFormsApp2
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            smoothBar1 = new ClassLibrary4.SmoothProgressBar();
            buttonWorker = new Button();
            smoothBarThread = new ClassLibrary4.SmoothProgressBar();
            John = new System.ComponentModel.BackgroundWorker();
            SuspendLayout();
            // 
            // smoothBar1
            // 
            smoothBar1.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            smoothBar1.BackColor = SystemColors.Window;
            smoothBar1.Location = new Point(158, 85);
            smoothBar1.Max = 100;
            smoothBar1.Min = 0;
            smoothBar1.Name = "smoothBar1";
            smoothBar1.Size = new Size(442, 59);
            smoothBar1.TabIndex = 0;
            smoothBar1.Text = "smoothProgressBar1";
            smoothBar1.Value = 0;
            // 
            // buttonWorker
            // 
            buttonWorker.Location = new Point(307, 316);
            buttonWorker.Name = "buttonWorker";
            buttonWorker.Size = new Size(142, 57);
            buttonWorker.TabIndex = 1;
            buttonWorker.Text = "Start test";
            buttonWorker.UseVisualStyleBackColor = true;
            buttonWorker.Click += button1_Click;
            // 
            // smoothBarThread
            // 
            smoothBarThread.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            smoothBarThread.BackColor = SystemColors.Window;
            smoothBarThread.Location = new Point(158, 202);
            smoothBarThread.Max = 100;
            smoothBarThread.Min = 0;
            smoothBarThread.Name = "smoothBarThread";
            smoothBarThread.Size = new Size(442, 59);
            smoothBarThread.TabIndex = 2;
            smoothBarThread.Text = "smoothProgressBar2";
            smoothBarThread.Value = 0;
            smoothBarThread.Click += smoothProgressBar2_Click;
            // 
            // John
            // 
            John.WorkerReportsProgress = true;
            John.DoWork += backgroundWorker1_DoWork;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(802, 450);
            Controls.Add(smoothBarThread);
            Controls.Add(buttonWorker);
            Controls.Add(smoothBar1);
            Name = "Form1";
            Text = "Form1";
            ResumeLayout(false);
        }

        #endregion
        private Button buttonWorker;
        private ClassLibrary4.SmoothProgressBar smoothBar1;
        private ClassLibrary4.SmoothProgressBar smoothBarThread;
        private System.ComponentModel.BackgroundWorker John;
    }
}
