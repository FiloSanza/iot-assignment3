import React, { useState, useEffect } from 'react';
import axios from 'axios';

async function RollerBlindController() {
  const [value, setValue] = useState(-1);
  const value_endpoint = 'http://localhost:1234/rollerblind/state' 

  useEffect(() => {
    async function getRollerBlindState() {
      const response = await axios.get(value_endpoint);
      const data = await response.json();
      setValue(data.value);
    }

    if (value === -1) {
      getRollerBlindState();
    }
  }, []);

  return (
    <div>
      <form>
        <label for="roller-blind-controller"> Roller Blinds: </label>
        <input id="roller-blind-controller" type="range" min="0" max="100" name="roller-blind-controller" value={{ value }} />
      </form>
    </div>
  )
}

export default RollerBlindController;