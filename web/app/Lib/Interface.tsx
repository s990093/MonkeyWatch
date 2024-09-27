// CompletionStatus Interface
export interface CompletionStatus {
  time: string; // Assuming ISO string format for datetime
  desc?: string; // Optional description
}

// Task Interface
export interface Task {
  name: string;
  time: string; // Assuming ISO string format for datetime
}

// DailyTask Interface extends Task
export interface DailyTask extends Task {
  id: number;
  task_type: "Work" | "Language" | "Study"; // Enum for task types
  completion_status?: CompletionStatus | null; // Optional OneToOne relationship
}

// WeeklyTask Interface
export interface WeeklyTask {
  id: number;
  task: DailyTask;
  day_of_week:
    | "Monday"
    | "Tuesday"
    | "Wednesday"
    | "Thursday"
    | "Friday"
    | "Saturday"
    | "Sunday";
}

export interface GroupedTasks {
  [key: string]: WeeklyTask[];
}
