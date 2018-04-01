using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace NDKLoggingTool
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        private Process _process;
        private ConsoleAutomator _automator;
        private void btnStartLogging_Click(object sender, EventArgs e)
        {
            var processStartInfo = new ProcessStartInfo
            {
                FileName = "cmd",
                Arguments = "/k adb logcat -s \"Gene\" *:E",
                RedirectStandardInput = true,
                RedirectStandardOutput = true,
                UseShellExecute = false,
                CreateNoWindow = true
            };

            _process = Process.Start(processStartInfo);
            _automator = new ConsoleAutomator(_process.StandardInput, _process.StandardOutput);

            // AutomatorStandardInputRead is your event handler
            _automator.StandardInputRead += Automator_StandardInputRead;
            _automator.StartAutomate(); 
        }

        private void Automator_StandardInputRead(object sender, ConsoleInputReadEventArgs e)
        {
            Invoke((MethodInvoker)delegate () {
                listView1.Items.Add(e.Input);
            });
        }

        private void btnStopLogging_Click(object sender, EventArgs e)
        {
            _automator.StandardInputRead -= Automator_StandardInputRead;
            _process.Kill();
        }
    }
}
