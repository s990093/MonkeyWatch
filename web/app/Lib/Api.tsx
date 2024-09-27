// utils/api.js

import axios from "axios";
import { GroupedTasks } from "./Interface";

const DEFAULT_URL = "https://lai.api.iside.space/";

const getApiUrl = (url: string) => {
  const ip = process.env.NEXT_PUBLIC_IP;
  const port = process.env.NEXT_PUBLIC_PORT;
  const http = process.env.NEXT_PUBLIC_HTTP;

  if (!ip && !port && !http) {
    return `${DEFAULT_URL}${url}`;
  }

  const finalIp = ip || "49.213.238.75";
  const finalPort = port || 8000;
  const finalHttp = http?.trim() !== "" ? http : "https";

  return `${finalHttp}://${finalIp}:${finalPort}/${url}`;
};

export const fetchGroupedTasks = async () => {
  const response = await axios.get<GroupedTasks>(
    getApiUrl("web/weekly-tasks/")
  );
  return { data: response.data, error: null };
};
