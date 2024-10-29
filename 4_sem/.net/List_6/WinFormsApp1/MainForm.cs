namespace WinFormsApp1
{
    public partial class MainForm : Form
    {
        public string Result { get; set; }
        public MainForm()
        {
            InitializeComponent();
        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            
            List<string> list = new List<string>();
            list.Add(textBox1.Text);   
            list.Add(textBox2.Text);
            list.Add(comboBox1.Text);
            if (checkBox1.Checked)
            {
                list.Add(checkBox1.Text);
            }
            else
            {
                list.Add(checkBox2.Text);
            }
            ChildForm form = new ChildForm(list);
            form.ShowDialog();
            
        }

        private void button3_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            int selectIndex = comboBox1.SelectedIndex;
            if (selectIndex == 0 || selectIndex == 1){
                checkBox1.Checked = true;
                checkBox2.Checked = false;
            }
            else if( selectIndex == 2 || selectIndex == 3)
            {
                checkBox1.Checked = false;
                checkBox2.Checked = true;
            }
        }

        
    }
}
