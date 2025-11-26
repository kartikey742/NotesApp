import React from "react";
import { Link, useNavigate } from "react-router-dom";
import "../css/navbar.css"; // optional for custom styles
import { Logout } from "./Logout";

const Navbar = () => {
  const navigate = useNavigate();


  return (
    <nav className="navbar2">
      <div className="nav-left">
        <h2 className="logo" onClick={()=>navigate('/')}>QuickNotes</h2>
      </div>

      <div className="nav-right">
        <Logout/>
      </div>
    </nav>
  );
};

export default Navbar;
