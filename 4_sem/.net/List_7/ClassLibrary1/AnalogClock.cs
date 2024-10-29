using System.Drawing;

namespace AnalogClock
{
    public partial class AnalogClock : UserControl
    {
        private const float PI = 3.141592654F;
        private DateTime dateTime;
        private float fRadius, fCenterX, fCenterY, fHourLength;
        private float fMinLength, fSecLength, fHourThickness, fMinThickness, fSecThickness;
        private bool bDraw5MinuteTicks = true;
        private bool bDraw1MinuteTicks = true;
        private float fTicksThickness = 2;
        private Color hrColor = Color.Black;
        private Color minColor = Color.Black;
        private Color secColor = Color.Black;
        private Color circleColor = Color.Black;
        private Color ticksColor = Color.Black;
        private Timer timer;

        public AnalogClock()
        {
            InitializeComponent();
            this.DoubleBuffered = true; // Zmniejsza migotanie podczas rysowania

            // Inicjalizacja i konfiguracja timera
            timer = new Timer();
            timer.Interval = 1000; // 1 sekunda
            timer.Tick += Timer_Tick;
            timer.Start();

            this.Load += AnalogClock_Load;
            this.Resize += AnalogClock_Resize;
            this.Paint += AnalogClock_Paint;
        }

        private void AnalogClock_Load(object sender, EventArgs e)
        {
            dateTime = DateTime.Now;
            this.AnalogClock_Resize(sender, e);
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            dateTime = DateTime.Now;
            this.Invalidate(); // Wywołuje wydarzenie Paint
        }

        private void DrawLine(float fThickness, float fLength, Color color, float fRadians, PaintEventArgs e)
        {
            e.Graphics.DrawLine(new Pen(color, fThickness),
                fCenterX - (float)(fLength / 9 * Math.Sin(fRadians)),
                fCenterY + (float)(fLength / 9 * Math.Cos(fRadians)),
                fCenterX + (float)(fLength * Math.Sin(fRadians)),
                fCenterY - (float)(fLength * Math.Cos(fRadians)));
        }

        private void DrawPolygon(float fThickness, float fLength, Color color, float fRadians, PaintEventArgs e)
        {
            PointF A = new PointF((float)(fCenterX + fThickness * 2 * Math.Sin(fRadians + PI / 2)),
                (float)(fCenterY - fThickness * 2 * Math.Cos(fRadians + PI / 2)));
            PointF B = new PointF((float)(fCenterX + fThickness * 2 * Math.Sin(fRadians - PI / 2)),
                (float)(fCenterY - fThickness * 2 * Math.Cos(fRadians - PI / 2)));
            PointF C = new PointF((float)(fCenterX + fLength * Math.Sin(fRadians)),
                (float)(fCenterY - fLength * Math.Cos(fRadians)));
            PointF D = new PointF((float)(fCenterX - fThickness * 4 * Math.Sin(fRadians)),
                (float)(fCenterY + fThickness * 4 * Math.Cos(fRadians)));
            PointF[] points = { A, D, B, C };
            e.Graphics.FillPolygon(new SolidBrush(color), points);
        }

        private void AnalogClock_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;

            float fRadHr = (dateTime.Hour % 12 + dateTime.Minute / 60F) * 30 * PI / 180;
            float fRadMin = (dateTime.Minute) * 6 * PI / 180;
            float fRadSec = (dateTime.Second) * 6 * PI / 180;

            DrawPolygon(this.fHourThickness, this.fHourLength, hrColor, fRadHr, e);
            DrawPolygon(this.fMinThickness, this.fMinLength, minColor, fRadMin, e);
            DrawLine(this.fSecThickness, this.fSecLength, secColor, fRadSec, e);

            for (int i = 0; i < 60; i++)
            {
                if (this.bDraw5MinuteTicks && i % 5 == 0)
                {
                    e.Graphics.DrawLine(new Pen(ticksColor, fTicksThickness),
                        fCenterX + (float)(this.fRadius / 1.50F * Math.Sin(i * 6 * PI / 180)),
                        fCenterY - (float)(this.fRadius / 1.50F * Math.Cos(i * 6 * PI / 180)),
                        fCenterX + (float)(this.fRadius / 1.75F * Math.Sin(i * 6 * PI / 180)),
                        fCenterY - (float)(this.fRadius / 1.75F * Math.Cos(i * 6 * PI / 180)));
                }
                else if (this.bDraw1MinuteTicks)
                {
                    e.Graphics.DrawLine(new Pen(ticksColor, fTicksThickness),
                        fCenterX + (float)(this.fRadius / 1.50F * Math.Sin(i * 6 * PI / 180)),
                        fCenterY - (float)(this.fRadius / 1.50F * Math.Cos(i * 6 * PI / 180)),
                        fCenterX + (float)(this.fRadius / 1.60F * Math.Sin(i * 6 * PI / 180)),
                        fCenterY - (float)(this.fRadius / 1.60F * Math.Cos(i * 6 * PI / 180)));
                }
            }
        }

        private void AnalogClock_Resize(object sender, EventArgs e)
        {
            float fDiameter = Math.Min(this.Width, this.Height);
            this.fRadius = fDiameter / 2;
            this.fCenterX = this.Width / 2;
            this.fCenterY = this.Height / 2;

            this.fHourLength = this.fRadius * 0.5F;
            this.fMinLength = this.fRadius * 0.7F;
            this.fSecLength = this.fRadius * 0.9F;

            this.fHourThickness = this.fRadius / 15;
            this.fMinThickness = this.fRadius / 20;
            this.fSecThickness = this.fRadius / 30;

            this.Invalidate(); // Wywołuje wydarzenie Paint
        }
    }
}
