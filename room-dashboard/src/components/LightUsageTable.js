import React, { useState, useEffect } from 'react';
import LightState from './LightState';
import axios from 'axios';

function LightUsageHistory() {
  const [data, setData] = useState(null);
  const light_history_endpoint = 'http://localhost:1234/light/history';

  useEffect(() => {
    const getLightHistory = async function () {
      const response = await axios.get(light_history_endpoint);
      const data = await response.json();
      setData(data);
    }

    if (data === null) {
      getLightHistory();
    }
  }, []);

  return (
    <table>
      <thead>
        <tr>
          <th>State</th>
          <th>From</th>
          <th>To</th>
        </tr>
      </thead>
      <tbody>
        { 
          data.map(row => {
            <tr>
              <td> <LightState light_on={ row.light_on }/> </td>
              <td> { row.from } </td>
              <td> { row.to } </td>
            </tr>
          })
        }
      </tbody>
    </table>
  );
}

export default LightUsageHistory;