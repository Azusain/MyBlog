import React from 'react';
import "./output.css";

function Header() {
  return (
    <>
        <div className="w-full h-20 grid grid-cols-4 bg-gura_main pl-2">
            <div className="col-start-2 py-3"><h1>@Azusaing</h1></div> 
            <div className="menu-item col-start-3 col-span-2 flex flex-row gap-3 px-2">
                <div>HOME</div>
                <div>WORKS</div>
                <div>BLOG</div>
                <div>CONTACT</div>
            </div>
        </div>
    </>
  );
}




export default Header;
