import React, { useState, useEffect } from 'react';
import axios from 'axios';

function RollerBlindController() {
  const [value, setValue] = useState(-1);
  const value_endpoint = 'http://localhost:1234/data';
  const rollerblinds_endpoint = 'http://localhost:1234/rollerblinds';

  const updateValue = async function(evt) {
    const new_value = evt.target.value;
    await axios.post(rollerblinds_endpoint, { angle: new_value });
    setValue(new_value);
  }

  const getRollerBlindState = async function () {
    const response = await axios.get(value_endpoint);
    const data = await response.json();
    setValue(data.value);
  }

  useEffect(() => {
    if (value === -1) {
      getRollerBlindState();
    }
  }, [value]);

  setTimeout(async () => await getRollerBlindState(), 500);
  
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