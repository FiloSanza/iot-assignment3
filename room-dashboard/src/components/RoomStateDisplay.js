import React, { useState, useEffect } from 'react';
import LightState from './LightState';
import axios from 'axios';

function RoomStateDisplay() {
  const [room_state, setRoomState] = useState(null);
  const room_state_endpoint = 'http://localhost:1234/data';

  useEffect(() => {
    const getRoomState = async function () {
      const response = await axios.get(room_state_endpoint);
      const data = await response.json();
      setRoomState(data);
    }

    if (value === null) {
      getRoomState();
    }
  }, []);

  if (room_state === null) {
    return <></>;
  }

  return (
    <div>
      <p> The light is: <LightState light_on={room_state.light_on} /> </p> 
      <p> The room is currently: <span> { room_state.empty ? 'empty' : 'occupied' } </span> </p>
    </div>
  )
}

export default RoomStateDisplay;