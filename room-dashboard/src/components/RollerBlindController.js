import React, { useState, useEffect } from 'react';
import axios from 'axios';

function RollerBlindController() {
  const [value, setValue] = useState(-1);
  const value_endpoint = 'http://localhost:5000/data';
  const rollerblinds_endpoint = 'http://localhost:5000/rollerblinds';

  const updateValue = async function(evt) {
    const new_value = evt.target.value;
    await axios.post(rollerblinds_endpoint, { angle: new_value });
    setValue(new_value);
  }

  const getRollerBlindState = async function () {
    const response = await axios.get(value_endpoint);
    const angle = response.data["angle"] / 180.0 * 100.0;
    setValue(angle);
  }

  useEffect(() => {
    if (value === -1) {
      setInterval(async () => await getRollerBlindState(), 500);
    }
  }, [value]);

  
  if (value === null) {
    return <></>;
  }

  return (
    <div className='w-1/2'>
      <form className='max-w-fit mx-auto'>
        <label htmlFor="roller-blind-controller"> Roller Blinds: </label>
        <input id="roller-blind-controller" type="range" min="0" max="100" name="roller-blind-controller" value={ value } onChange={ updateValue } />
      </form>
    </div>
  )
}

export default RollerBlindController;