namespace Z1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            this.SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.UserPaint | ControlStyles.OptimizedDoubleBuffer, true);
        }

        public void draw_Clock_Hand(Graphics g, SolidBrush brush, int rec_width,
            int rec_height, float angle, int centerX, int centerY, bool rotate)
        {
            var rectX = centerX - rec_width / 2;
            var rectY = centerY - rec_height;

            if (rotate)
            {
                g.TranslateTransform(centerX, centerY);
                g.RotateTransform(angle);
                g.TranslateTransform(-centerX, -centerY);
            }

            g.FillRectangle(brush, rectX, rectY, rec_width, rec_height);

            if (rotate)
            {
                g.ResetTransform();
            }
        }

        float secondsRotation = 0;
        float minutesRotation = 0;
        float hoursRotation = 0;

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            var width = this.ClientSize.Width;
            var height = this.ClientSize.Height;

            var centerX = width / 2;
            var centerY = height / 2;

            double size = 0.4;
            int radius = (int)(Math.Min(width, height) * size);

            int rectangleWidth = 10;
            int rectangleHeight = radius;

            var blackPen = new Pen(Color.Black, 4);
            var blackBrush = new SolidBrush(Color.Black);
            var redBrush = new SolidBrush(Color.Red);
            var greenBrush = new SolidBrush(Color.Green);

            e.Graphics.DrawEllipse(blackPen, centerX - radius, centerY - radius, 2 * radius, 2 * radius);

            // Hour hand clock
            draw_Clock_Hand(e.Graphics, blackBrush, rectangleWidth, rectangleHeight, hoursRotation, centerX, centerY, true);

            // Minute hand clock
            draw_Clock_Hand(e.Graphics, redBrush, (int)(rectangleWidth * 0.5), (int)(rectangleHeight * 0.8), minutesRotation, centerX, centerY, true);

            // Second hand clock
            draw_Clock_Hand(e.Graphics, greenBrush, (int)(rectangleWidth * 0.2), rectangleHeight, secondsRotation, centerX, centerY, true);

            blackPen.Dispose();
            blackBrush.Dispose();
            redBrush.Dispose();
            greenBrush.Dispose();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            secondsRotation += 6; 
            if (secondsRotation >= 360)
            {
                secondsRotation = 0;
                minutesRotation += 6; 
            if (minutesRotation >= 360)
            {
                minutesRotation = 0;
                hoursRotation += 30; 
            }
            if (hoursRotation >= 360)
            {
                hoursRotation = 0;
            }
            Invalidate();
        }

        void Form1_Load(object sender, EventArgs e)
        {
            
        }

        void Form1_Resize(object sender, EventArgs e)
        {
            this.Invalidate();
        }
    }
}
