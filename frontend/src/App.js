import logo from './logo.svg';
import './css/login.css';
import { Routes, Route } from 'react-router-dom';
import Login from './pages/Login'
import Signup from './pages/Signup'
import { CheckAuth } from './pages/CheckAuth';
import {Dashboard} from './pages/Dashboard'
import { Home } from './pages/Home';
import { useLocation } from 'react-router-dom';
function App() {
  const { pathname } = useLocation();
  console.log(pathname);
  
  return (
    <div className="App">

      <Routes>
        <Route path="/" element={<Home />}/>
        <Route path="/login" element={<CheckAuth><Login /></CheckAuth>} />
        <Route path="/signup" element={<CheckAuth><Signup/></CheckAuth>} />
        <Route path="/dashboard" element={<CheckAuth><Dashboard /></CheckAuth>} />
      </Routes>
    </div>
  );
}

export default App;
