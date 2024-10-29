using System;
using System.Drawing;
using System.ComponentModel;

public class SmoothProgressBar : Component
{
    // Properties for Min, Max, and Value
    private int minValue = 0;
    private int maxValue = 100;
    private int value = 0;

    public int MinValue
    {
        get { return minValue; }
        set { minValue = value; }
    }

    public int MaxValue
    {
        get { return maxValue; }
        set { maxValue = value; }
    }

    public int Value
    {
        get { return value; }
        set
        {
            this.value = value;
            Invalidate(); // Trigger repainting
        }
    }

    // Constructor
    public SmoothProgressBar()
    {
        this.SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.UserPaint | ControlStyles.OptimizedDoubleBuffer, true);
    }

    // Paint event handler to draw the progress bar
    protected override void OnPaint(PaintEventArgs e)
    {
        base.OnPaint(e);

        // Get the dimensions of the control
        var width = this.Width;
        var height = this.Height;

        // Calculate the progress ratio
        double progressRatio = (double)(value - minValue) / (maxValue - minValue);

        // Draw the progress bar using a gradient brush
        using (var brush = new LinearGradientBrush(
            new Point(0, 0),
            new Point(width, 0),
            Color.White,
            Color.Blue))
        {
            var progressBarWidth = (int)(width * progressRatio);
            e.Graphics.FillRectangle(brush, 0, 0, progressBarWidth, height);
        }

        // Draw the border around the progress bar
        using (var pen = new Pen(Color.Black, 1))
        {
            e.Graphics.DrawRectangle(pen, 0, 0, width - 1, height - 1);
        }
    }
}