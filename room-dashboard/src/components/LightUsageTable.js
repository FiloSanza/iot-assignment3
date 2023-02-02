import React, { useState, useEffect } from 'react';
import LightState from './LightState';
import axios from 'axios';

function LightUsageHistory() {
  const [data, setData] = useState(null);
  const light_history_endpoint = 'http://localhost:1234/data';

  useEffect(() => {
    const getLightHistory = async function () {
      const response = await axios.get(light_history_endpoint);
      const data = await response.json();
      setData(data.light_logs);
    }

    if (data === null) {
      getLightHistory();
    }
  }, []);

  if (data === null) {
    return <></>;
  }

  return (
    <table>
      <thead>
        <tr>
          <th>State</th>
          <th>Since</th>
        </tr>
      </thead>
      <tbody>
        { 
          data.map(row => {
            <tr>
              <td> <LightState light_on={ row.state }/> </td>
              <td> { row.ts } </td>
            </tr>
          })
        }
      </tbody>
    </table>
  );
}

export default LightUsageHistory;