using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assigment6
{
    /// <summary>
    /// Priority for the tasks
    /// </summary>
    enum Priority { Less_important, Medium_important, High_important}

    /// <summary>
    /// Class with the data of the tasks
    /// </summary>
    class Task
    {
        private string description;

        private DateTime dateTime;

        private Priority priority;

        /// <summary>
        /// Set the data for the task
        /// </summary>
        /// <param name="dateTime">Date time for the task</param>
        /// <param name="description">Description of the task</param>
        /// <param name="priority">Priority for the task</param>
        public Task(DateTime dateTime, string description, Priority priority)
        {
            this.dateTime = dateTime;
            this.description = description;
            this.priority = priority;
        }

        //Getters
        public string Description
        {
            get { return description; }
        }

        public DateTime DateTime
        {
            get { return dateTime; }
        }

        public Priority Priority
        {
            get { return priority; }
        }

        /// <summary>
        /// Put all the data togheter with the correct formatting to be shown in the listbox
        /// </summary>
        /// <returns>Constructed string</returns>
        public override string ToString()
        {
            return "den " + dateTime.ToString("MMM ddd d yyyy") + Spaces(8) + dateTime.ToString("HH:mm") + " " + RemoveUnderScores(this.priority) + Spaces(8) + description;
        }

        /// <summary>
        /// Remove the underscores from the name of a priorty enum
        /// </summary>
        /// <param name="priority">The enum to process</param>
        /// <returns>Priority name without underscores</returns>
        private string RemoveUnderScores(Priority priority)
        {
            string source = priority.ToString();
            string result = "";

            for (int i = 0; i < source.Length; i++) result += ((source[i] == '_') ? " " : source[i].ToString());

            return result;
        }

        /// <summary>
        /// Spaces to pad strings
        /// </summary>
        /// <param name="amount">amount of spaces</param>
        /// <returns>Spaces</returns>
        private string Spaces(int amount)
        {
            string result = "";

            for (int i = 0; i < amount; i++) result += " ";
            
            return result;
        }
    }
}
