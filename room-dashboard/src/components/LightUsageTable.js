import React, { useState, useEffect } from 'react';
import LightState from './LightState';
import axios from 'axios';

function LightUsageHistory() {
  const [data, setData] = useState(null);
  const light_history_endpoint = 'http://localhost:5000/data';

  const getLightHistory = async function () {
    const response = await axios.get(light_history_endpoint);
    setData(response.data['light_logs']);
  }

  useEffect(() => {
    if (data === null) {
      setInterval(async () => await getLightHistory(), 500);
    }
  }, [data]);

  if (data === null) {
    return <></>;
  }

  return (
    <table className='mx-auto'>
      <thead>
        <tr>
          <th className='w-40'>State</th>
          <th className='w-40'>Since</th>
        </tr>
      </thead>
      <tbody>
        { 
          data.map(row => {
            return (
              <tr key={ row.ts }>
                <td className='w-40'> <LightState center light_on={ Number.parseInt(row.state) }/> </td>
                <td className='w-40'> { row.ts } </td>
              </tr>
            );
          })
        }
      </tbody>
    </table>
  );
}

export default LightUsageHistory;