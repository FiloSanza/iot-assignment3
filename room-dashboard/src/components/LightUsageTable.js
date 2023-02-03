import React, { useState, useEffect } from 'react';
import LightState from './LightState';
import axios from 'axios';

function LightUsageHistory() {
  const [data, setData] = useState(
    [{'state': 0, 'ts': '03/02/2023 12:48:53'}, {'state': 1, 'ts': '03/02/2023 12:49:29'}, {'state': 0, 'ts': '03/02/2023 12:49:31'}, {'state': 1, 'ts': '03/02/2023 12:50:03'}, {'state': 0, 'ts': '03/02/2023 12:50:05'}, {'state': 1, 'ts': '03/02/2023 12:50:06'}, {'state': 0, 'ts': '03/02/2023 12:50:07'}, {'state': 1, 'ts': '03/02/2023 12:50:08'}, {'state': 0, 'ts': '03/02/2023 12:50:10'}, {'state': 1, 'ts': '03/02/2023 12:50:14'}, {'state': 0, 'ts': '03/02/2023 12:50:16'}, {'state': 1, 'ts': '03/02/2023 12:50:18'}, {'state': 0, 'ts': '03/02/2023 12:50:21'}]
  );
  const light_history_endpoint = 'http://localhost:1234/data';

  useEffect(() => {
    const getLightHistory = async function () {
      const response = await axios.get(light_history_endpoint);
      const data = await response.json();

      setData(data['light_logs']);
    }

    if (data === null) {
      getLightHistory();
    }
  }, [data]);

  if (data === null) {
    return <></>;
  }

  console.log(data);

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
                <td className='w-40'> <LightState center light_on={ row.state }/> </td>
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