import React from 'react'

interface MainConInterface {
    children?: React.ReactNode;
    width: string;
    height: string;
    inner_layout: string;
    // only for testing 
    options?: string;
}

// width: the width of the main content inside
// inner_layout: similar to the variable above
const MainCon: React.FC<MainConInterface> = (props) => {
    return (
        <div className={`flex w-full h-[${props.height}] ${props.options} justify-center`}>
            <div className={`w-[${props.width}] h-full ${props.inner_layout}` }>
                {props.children}
            </div>
        </div>
    )
}

export default MainCon;