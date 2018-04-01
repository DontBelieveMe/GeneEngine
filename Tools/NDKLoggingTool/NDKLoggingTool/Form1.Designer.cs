namespace NDKLoggingTool
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnStartLogging = new System.Windows.Forms.Button();
            this.btnStopLogging = new System.Windows.Forms.Button();
            this.listView1 = new System.Windows.Forms.ListView();
            this.SuspendLayout();
            // 
            // btnStartLogging
            // 
            this.btnStartLogging.Location = new System.Drawing.Point(12, 12);
            this.btnStartLogging.Name = "btnStartLogging";
            this.btnStartLogging.Size = new System.Drawing.Size(96, 23);
            this.btnStartLogging.TabIndex = 2;
            this.btnStartLogging.Text = "Start Logging";
            this.btnStartLogging.UseVisualStyleBackColor = true;
            this.btnStartLogging.Click += new System.EventHandler(this.btnStartLogging_Click);
            // 
            // btnStopLogging
            // 
            this.btnStopLogging.Location = new System.Drawing.Point(114, 12);
            this.btnStopLogging.Name = "btnStopLogging";
            this.btnStopLogging.Size = new System.Drawing.Size(93, 23);
            this.btnStopLogging.TabIndex = 3;
            this.btnStopLogging.Text = "Stop Logging";
            this.btnStopLogging.UseVisualStyleBackColor = true;
            this.btnStopLogging.Click += new System.EventHandler(this.btnStopLogging_Click);
            // 
            // listView1
            // 
            this.listView1.Alignment = System.Windows.Forms.ListViewAlignment.Left;
            this.listView1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listView1.LabelWrap = false;
            this.listView1.Location = new System.Drawing.Point(12, 50);
            this.listView1.Name = "listView1";
            this.listView1.ShowGroups = false;
            this.listView1.Size = new System.Drawing.Size(683, 380);
            this.listView1.TabIndex = 4;
            this.listView1.UseCompatibleStateImageBehavior = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(707, 442);
            this.Controls.Add(this.listView1);
            this.Controls.Add(this.btnStopLogging);
            this.Controls.Add(this.btnStartLogging);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Button btnStartLogging;
        private System.Windows.Forms.Button btnStopLogging;
        private System.Windows.Forms.ListView listView1;
    }
}

