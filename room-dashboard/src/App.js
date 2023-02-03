import LightUsageTable  from './components/LightUsageTable'
import RollerBlindController from './components/RollerBlindController'
import RoomStateDisplay from './components/RoomStateDisplay'

function App() {
  return (
    <div className='w-full p-5 flex flex-col items-center'>
      <div className='w-full flex flex-row justify-center'>
        <RoomStateDisplay />
        <RollerBlindController />
      </div>
      <div className='w-1/2 mt-10'>
        <LightUsageTable />
      </div>
    </div>
  );
}

export default App;
