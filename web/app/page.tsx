"use client";
import { useEffect, useState } from "react";
import Card from "./Card";
import { GroupedTasks } from "./Lib/Interface";
import { mockData } from "./Lib/Mock";
import { Stars } from "@react-three/drei";

const Home: React.FC = () => {
  const [groupedTasks, setGroupedTasks] = useState<GroupedTasks>(mockData);

  // useEffect(() => {
  //   const fetchTasks = async () => {
  //     try {
  //       const response = await fetchGroupedTasks();
  //       setGroupedTasks(response.data);
  //     } catch (error) {
  //       console.error("Error fetching tasks:", error);
  //     }
  //   };

  //   fetchTasks();
  // }, []);

  return (
    <div className="w-full flex flex-col p-4">
      <h1 className="text-4xl font-bold text-center mb-10">TODOLIST</h1>
      <div className="grid grid-cols-1  gap-10">
        {Object.keys(groupedTasks).map((day) => (
          <div key={day} className="p-6 rounded-lg  w-full">
            <h2 className="text-2xl font-bold text-indigo-700 mb-4 text-center">
              {day}
            </h2>
            <div className="flex flex-col items-center">
              <Card
                taskList={mockData[day].map((weeklyTask) => weeklyTask.task)}
              />
            </div>
          </div>
        ))}
      </div>
    </div>
  );
};

export default Home;
