using System.Drawing.Drawing2D;

namespace ClassLibrary4
{
    public class SmoothProgressBar : Control
    {

        private int minimum = 0;
        private int maximum = 100;
        private float value = 0;

     
        public int Max
        {
            get { return maximum; }
            set
            {
                maximum = value;
                Invalidate();
            }
        }

        public int Min
        {
            get { return minimum; }
            set
            {
                minimum = value;
                Invalidate();
            }
        }

        public int Value
        {
            get { return (int)value; }
            set { this.value = value;
                Invalidate();
            }
        }

        protected override void OnPaint(PaintEventArgs e)
        {

            var width = this.Width;
            var height = this.Height;
            float range = maximum - minimum;
            //MessageBox.Show(range.ToString());
            float percentage = value / range;
            float fillwidth = (float)width * percentage + 1;
            //MessageBox.Show(range.ToString());

            using (var gradientBrush = new LinearGradientBrush(
                new Rectangle(0, 0, (int)fillwidth, height),
                Color.LightBlue,
                Color.Blue, // Start color
                 // End color
                LinearGradientMode.Horizontal))
            {
                e.Graphics.FillRectangle(gradientBrush, 0, 0, fillwidth, height);
            }
            // Dodaj tekst na środku paska
            string text = $"{(int)(percentage*100)}%";
            using (var font = new Font("Arial", 12, FontStyle.Bold))
            {
                var textSize = e.Graphics.MeasureString(text, font);
                var textX = (width - textSize.Width) / 2;
                var textY = (height - textSize.Height) / 2;

                // Draw the text outline (black)
                using(var outlineBrush = new SolidBrush(Color.Black))
                {
                    e.Graphics.DrawString(text, font, outlineBrush, textX - 1, textY);
                    e.Graphics.DrawString(text, font, outlineBrush, textX + 1, textY);
                    e.Graphics.DrawString(text, font, outlineBrush, textX, textY - 1);
                    e.Graphics.DrawString(text, font, outlineBrush, textX, textY + 1);
                }

                // Draw the main text (white)
                using (var textBrush = new SolidBrush(Color.White))
                {
                    e.Graphics.DrawString(text, font, textBrush, textX, textY);
                }
            }
            base.OnPaint(e);
        }
        
    }
}
