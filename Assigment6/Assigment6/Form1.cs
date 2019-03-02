using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Assigment6
{
    /// <summary>
    /// The main window with all controls to mainpulate a list of tasks
    /// </summary>
    public partial class Form1 : Form
    {
        TaskManager taskManager;

        /// <summary>
        /// Set the tool tip, update the clock label, initalize the task manager and add all the priority types without under scores
        /// </summary>
        public Form1()
        {
            InitializeComponent();

            toolTip1.SetToolTip(dateTimePicker1, "Select the date for the task");

            UpdateClockLabel();

            taskManager = new TaskManager();

            string[] priorityies = { Priority.Less_important.ToString(), Priority.Medium_important.ToString(), Priority.High_important.ToString() };
            for (int i = 0; i < priorityies.Length; i++)
            {
                string source = priorityies[i];
                string result = "";

                for (int j = 0; j < source.Length; j++) result += ((source[j] == '_') ? " " : source[j].ToString());

                PrioritySelector.Items.Add(result);
            }
            
            SetButtonMode(false);
        }

        /// <summary>
        /// Clear all lists so that it is a new session
        /// </summary>
        private void Reset()
        {
            taskManager.Clear();
            ToDos.Items.Clear();
            SetButtonMode(false);
        }

        /// <summary>
        /// Update the listbox with the taskmanagers elemetnsh
        /// </summary>
        private void UpdateList()
        {
            ToDos.Items.Clear();
            for (int i = 0; i < taskManager.Size; i++) ToDos.Items.Add(taskManager.Get(i).ToString());
        }
        
        /// <summary>
        /// Every tick, update the clock label
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timer1_Tick(object sender, EventArgs e)
        {
            UpdateClockLabel();
        }

        /// <summary>
        /// Set the clocklabels text to the current date time, with the millitary clock format("HH")
        /// </summary>
        private void UpdateClockLabel()
        {
            ClockLabel.Text = DateTime.Now.ToString("HH:mm:ss");
        }

        /// <summary>
        /// Take the data from the fields and add the task and reset the fields
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void AddButton_Click(object sender, EventArgs e)
        {
            Priority picked = Priority.Less_important;
            if (PrioritySelector.SelectedIndex == 0) picked = Priority.Less_important;
            if (PrioritySelector.SelectedIndex == 1) picked = Priority.Medium_important;
            if (PrioritySelector.SelectedIndex == 2) picked = Priority.High_important;

            taskManager.Add(dateTimePicker1.Value, DescriptionBox.Text, picked);
            UpdateList();

            DescriptionBox.Text = "";
            PrioritySelector.SelectedIndex = 0;
            dateTimePicker1.Value = DateTime.Now;
        }

        /// <summary>
        /// If the selectedindex from the listbox is in the correct interval, then ask if the user is sure and dellete
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void DeleteButton_Click(object sender, EventArgs e)
        {
            if (ToDos.SelectedIndex >= 0 && ToDos.SelectedIndex < taskManager.Size)
            {
                if (MessageBox.Show("Are you sure?", "Are you sure?", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    taskManager.Delete(ToDos.SelectedIndex);
                    UpdateList();
                    SetButtonMode(false);
                }
            }
        }

        /// <summary>
        ///  if the correct interval is selected put the tasks data into the fields to be modfied
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ChangeButton_Click(object sender, EventArgs e)
        {
            if (ToDos.SelectedIndex >= 0 && ToDos.SelectedIndex < taskManager.Size)
            {
                DescriptionBox.Text = taskManager.Get(ToDos.SelectedIndex).Description;
                dateTimePicker1.Value = taskManager.Get(ToDos.SelectedIndex).DateTime;

                if (taskManager.Get(ToDos.SelectedIndex).Priority == Priority.Less_important) PrioritySelector.SelectedIndex = 0;
                if (taskManager.Get(ToDos.SelectedIndex).Priority == Priority.Medium_important) PrioritySelector.SelectedIndex = 1;
                if (taskManager.Get(ToDos.SelectedIndex).Priority == Priority.High_important) PrioritySelector.SelectedIndex = 2;

                taskManager.Delete(ToDos.SelectedIndex);
                UpdateList();
                SetButtonMode(false);
            }
        }

        /// <summary>
        /// activate the add and delete buttons
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ToDos_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetButtonMode(true);
        }

        /// <summary>
        /// Set the enabled state of the buttons
        /// </summary>
        /// <param name="mode">the state to set</param>
        private void SetButtonMode(bool mode)
        {
            DeleteButton.Enabled = mode;
            ChangeButton.Enabled = mode;
        }

        private void ClockLabel_Click(object sender, EventArgs e)
        {

        }

        /// <summary>
        /// Restart the lists 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Reset();
        }

        /// <summary>
        /// if the user presses exit or uses shortcut ask if they are sure and shut down
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("Are you sure?", "Are you sure?", MessageBoxButtons.OKCancel) == DialogResult.OK)
                this.Close();
        }

        private void toolTip1_Popup(object sender, PopupEventArgs e)
        {

        }

        /// <summary>
        /// Open about box with assembly data
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void omToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AboutBox1 a = new AboutBox1();
            a.Show();
        }
    }
}
