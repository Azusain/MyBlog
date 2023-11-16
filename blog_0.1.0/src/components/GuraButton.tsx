import React from "react";

interface GuraButtonInterface{
    text: string
    onClick?: React.MouseEventHandler<HTMLElement>
}

const GuraButton: React.FC<GuraButtonInterface> = (props) => {

    return(
        <button 
            className="bg-gura_main p-2 text-white hover:bg-sky-800 duration-200 my-2 shadow-lg"
            onClick={props.onClick}    
        >
            {props.text}
        </button>
    )
}

export default GuraButton;