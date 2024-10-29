using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinFormsApp1
{
    public partial class ChildForm : Form
    {
        private string Parameter { get; set; }

        public ChildForm(List<string> items)
        {
            InitializeComponent();
            label2.Text = items[0];
            label3.Text = items[1];
            label4.Text = items[2];
            label5.Text = items[3];
            
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        
    }
}
