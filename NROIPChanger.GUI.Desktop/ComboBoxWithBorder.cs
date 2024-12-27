using System.ComponentModel;

namespace NROIPChanger.GUI.Desktop
{
    internal class ComboBoxWithBorder : ComboBox
    {
        const int WM_PAINT = 0xF;
        Color borderColor = Color.Black;

        [DefaultValue(typeof(Color), "Black")]
        public Color BorderColor
        {
            get => borderColor;
            set
            {
                borderColor = value;
                Invalidate();
            }
        }

        protected override void WndProc(ref Message m)
        {
            base.WndProc(ref m);
            if (m.Msg != WM_PAINT || DropDownStyle == ComboBoxStyle.Simple)
                return;
            using var g = Graphics.FromHwnd(Handle);
            using var p = new Pen(BorderColor);
            g.DrawRectangle(p, 0, 0, Width - 1, Height - 1);
        }
    }

}
