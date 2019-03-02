using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assigment6
{
    /// <summary>
    /// Manipulates a list of tasks
    /// </summary>
    class TaskManager
    {
        private List<Task> tasks;

        /// <summary>
        /// Initialize the list
        /// </summary>
        public TaskManager()
        {
            tasks = new List<Task>();
        }

        /// <summary>
        /// Get the size of the list
        /// </summary>
        public int Size
        {
            get { return tasks.Count; }
        }

        /// <summary>
        /// Clear the list
        /// </summary>
        public void Clear()
        {
            tasks.Clear();
        }

        /// <summary>
        /// Checks if the input data is correct and adds a task with the parameters if it is
        /// </summary>
        /// <param name="dateTime">Tasks datatime</param>
        /// <param name="description">Descripton of the task</param>
        /// <param name="priority">Priority of the task</param>
        /// <returns>If it was added or not</returns>
        public bool Add(DateTime dateTime, string description, Priority priority)
        {
            if (dateTime == null || description == null) return false;
            tasks.Add(new Task(dateTime, description, priority));
            return true;
        }

        /// <summary>
        /// Delete a task if the index is within the correct intervall
        /// </summary>
        /// <param name="index">Index to be deleted</param>
        /// <returns>If it was deleted</returns>
        public bool Delete(int index)
        {
            if (index < 0 || index >= tasks.Count) return false;
            tasks.RemoveAt(index);
            return true;
        }

        /// <summary>
        /// Get a task at an index if it is within the correct interval
        /// </summary>
        /// <param name="index">Index to get from</param>
        /// <returns></returns>
        public Task Get(int index)
        {
            if (index < 0 || index >= tasks.Count) return null;
            return tasks[index];
        }
    }
}
