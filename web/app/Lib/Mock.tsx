import { GroupedTasks } from "./Interface";

export const mockData: GroupedTasks = {
  Monday: [
    {
      id: 1,
      task: {
        id: 1,
        name: "Morning Yoga",
        time: "2024-09-24T06:00:00Z",
        task_type: "Work",
        completion_status: {
          time: "2024-09-24T07:00:00Z",
          desc: "Completed successfully",
        },
      },
      day_of_week: "Monday",
    },
    {
      id: 2,
      task: {
        id: 2,
        name: "Japanese Vocabulary Review",
        time: "2024-09-24T08:00:00Z",
        task_type: "Language",
        completion_status: {
          time: "2024-09-24T08:30:00Z",
        },
      },
      day_of_week: "Monday",
    },
  ],
  Tuesday: [
    {
      id: 3,
      task: {
        id: 3,
        name: "Reading Chapter 5 of Data Science Book",
        time: "2024-09-24T10:00:00Z",
        task_type: "Study",
        completion_status: null,
      },
      day_of_week: "Tuesday",
    },
  ],
  Wednesday: [
    {
      id: 4,
      task: {
        id: 1,
        name: "Team Meeting",
        time: "2024-09-25T09:00:00Z",
        task_type: "Work",
        completion_status: {
          time: "2024-09-25T10:00:00Z",
          desc: "Meeting concluded with action items",
        },
      },
      day_of_week: "Wednesday",
    },
  ],
};
