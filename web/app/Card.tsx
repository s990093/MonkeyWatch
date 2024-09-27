"use client";
import React, { useEffect, useState } from "react";
import { DailyTask } from "./Lib/Interface";

interface CardProps {
  taskList: DailyTask[];
}

const Card: React.FC<CardProps> = ({ taskList }) => {
  const [tasks, setTasks] = useState<DailyTask[]>([]);

  // Initialize the tasks state from the taskList prop
  useEffect(() => {
    setTasks(taskList);
  }, [taskList]);

  // Handle status change for individual tasks
  const handleStatusChange = (taskId: number) => {
    setTasks((prevTasks) =>
      prevTasks.map((task) =>
        task.id === taskId
          ? {
              ...task,
              completion_status: task.completion_status
                ? null // Toggle status: If it's complete, mark as incomplete
                : { time: new Date().toISOString(), desc: "Task completed" }, // Set completion status
            }
          : task
      )
    );
  };
  return (
    <div className="task-card-container bg-white shadow-lg rounded-xl p-6 w-3/4">
      <h2 className="text-2xl font-semibold text-indigo-600 mb-6 text-center">
        Daily Tasks
      </h2>
      {tasks.map((dailyTask, index) => (
        <div
          key={`${dailyTask.id}-${index}`}
          className="flex items-center justify-between mb-6 bg-gray-50 p-4 rounded-lg shadow-sm hover:shadow-md transition-shadow duration-200"
        >
          <div>
            <h3 className="text-lg font-bold text-indigo-700 mb-2">
              {dailyTask.name}
            </h3>
            <p className="text-gray-500 mb-1">
              Type:{" "}
              <span className="text-gray-800 font-medium">
                {dailyTask.task_type}
              </span>
            </p>
            <p className="text-gray-500 mb-1">
              Time:{" "}
              <span className="text-gray-800 font-medium">
                {new Date(dailyTask.time).toLocaleString()}
              </span>
            </p>
            {dailyTask.completion_status &&
              dailyTask.completion_status.desc && (
                <p className="text-gray-600 italic">
                  {dailyTask.completion_status.desc}
                </p>
              )}
          </div>

          {/* Single Radio button for task status */}
          <div className="ml-6">
            <label className="flex items-center space-x-2">
              <input
                type="radio"
                name={`task-status-${index}`}
                checked={!!dailyTask.completion_status}
                onChange={() => handleStatusChange(dailyTask.id)}
                className="form-radio h-5 w-5 text-green-600"
              />
            </label>
          </div>
        </div>
      ))}
    </div>
  );
};

export default Card;
