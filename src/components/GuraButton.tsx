import React from 'react'


interface GuraButtonInterface{
    text: string
}

const GuraButton: React.FC<GuraButtonInterface> = (porps) => {

    return(
        <button className="bg-gura_main p-2 text-white hover:bg-sky-800 duration-200 my-2">
            {porps.text}
        </button>
    )
}

export default GuraButton;