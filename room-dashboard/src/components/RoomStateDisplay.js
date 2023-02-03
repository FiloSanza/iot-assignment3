import React, { useState, useEffect } from 'react';
import LightState from './LightState';
import axios from 'axios';

function RoomStateDisplay() {
  const [room_state, setRoomState] = useState(
    {'light_logs': [{'state': 0, 'ts': '03/02/2023 12:48:53'}, {'state': 1, 'ts': '03/02/2023 12:49:29'}, {'state': 0, 'ts': '03/02/2023 12:49:31'}, {'state': 1, 'ts': '03/02/2023 12:50:03'}, {'state': 0, 'ts': '03/02/2023 12:50:05'}, {'state': 1, 'ts': '03/02/2023 12:50:06'}, {'state': 0, 'ts': '03/02/2023 12:50:07'}, {'state': 1, 'ts': '03/02/2023 12:50:08'}, {'state': 0, 'ts': '03/02/2023 12:50:10'}, {'state': 1, 'ts': '03/02/2023 12:50:14'}, {'state': 0, 'ts': '03/02/2023 12:50:16'}, {'state': 1, 'ts': '03/02/2023 12:50:18'}, {'state': 0, 'ts': '03/02/2023 12:50:21'}], 'pir_state': 0, 'light_state': 0, 'rollerblinds_state': 100}
  );
  const room_state_endpoint = 'http://localhost:1234/data';

  useEffect(() => {
    const getRoomState = async function () {
      const response = await axios.get(room_state_endpoint);
      const data = await response.json();
      setRoomState(data);
    }

    if (room_state === null) {
      getRoomState();
    }
  }, [room_state]);

  if (room_state === null) {
    return <></>;
  }

  return (
    <div className='w-1/2'>
      <div className='mx-auto max-w-fit'>
        <p> The light is: <LightState light_on={room_state.light_state} /> </p> 
        <p> The room is currently: <span> { room_state.pir ? 'Occupied' : 'Empty' } </span> </p>
      </div>
    </div>
  )
}

export default RoomStateDisplay;