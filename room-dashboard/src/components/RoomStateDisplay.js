import React, { useState, useEffect } from 'react';
import LightState from './LightState';
import axios from 'axios';

function RoomStateDisplay() {
  const [room_state, setRoomState] = useState(null);
  const room_state_endpoint = 'http://localhost:5000/data';
  const light_endpoint = 'http://localhost:5000/light';

  const getRoomState = async function () {
    const response = await axios.get(room_state_endpoint);
    setRoomState(response.data);
  }
  
  const toggleLight = async function () {
    const new_state = Number.parseInt(room_state.light) ? "0" : "1";
    await axios.post(light_endpoint, { light: new_state })
      .then(async res => await getRoomState());
  }

  useEffect(() => {
    if (room_state === null) {
      setInterval(async () => await getRoomState(), 500);
    }
  }, [room_state]);


  if (room_state === null) {
    return <></>;
  }

  return (
    <div className='w-1/2'>
      <div className='mx-auto max-w-fit'>
        <p onClick={toggleLight}> The light is: <LightState light_on={Number.parseInt(room_state.light)} /> </p> 
        <p> The room is currently: <span> { room_state.pir_state ? 'Occupied' : 'Empty' } </span> </p>
      </div>
    </div>
  )
}

export default RoomStateDisplay;