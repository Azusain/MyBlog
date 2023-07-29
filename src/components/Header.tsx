import React from 'react';
import { Navigate, useNavigate } from 'react-router-dom';
import { hover } from '@testing-library/user-event/dist/hover';

// Bind name of each menubar item to a route 
class MenuItem {
    constructor(key:string, route:string) {
        this.keyword = key;
        this.route = route;
    }
    
    keyword: string;
    route: string;
}

const Header: React.FC = () => {
    let navi = useNavigate()

    const menu_items = [
        {keyword: 'HOME', route: '/'}, 
        {keyword: 'BLOGS',route: '/blogs'}, 
        {keyword: 'CONTACT', route: '/contact'}
    ];

    return (
        <>
            <div className="w-full h-20 grid grid-cols-4 bg-gura_main pl-2">
                <div className="col-start-2 py-3"><h1>@Azusaing</h1></div> 
                <div className="menu-item col-start-3 col-span-2 flex flex-row gap-3 px-2">
                    {menu_items.map( (menu_item: MenuItem, idx: number) => {
                        return (
                            <div 
                                key={idx}
                                onClick={() => {navi(menu_item.route)}}
                                
                            >{menu_item.keyword}</div>
                        )
                    })}
                </div>
            </div>
        </>
    );
}

export default Header;
