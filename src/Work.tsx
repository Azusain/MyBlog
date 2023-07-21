import React from 'react'
import MainCon from './components/MainCon'
import './output.css'

import img1 from "./img/work/9.jpg"
import img2 from "./img/work/10.jpg"
import img3 from "./img/work/11.jpg"
import img4 from "./img/work/12.jpg"
import img5 from "./img/work/13.jpg"
import img6 from "./img/work/14.jpg"
import img7 from "./img/work/15.jpg"
import img8 from "./img/work/16.jpg"



const Work: React.FC = () => {

    const images = [img1, img2, img3, img4, img5, img6, img7, img8]


    return (
        <>
            <MainCon width='46%' height='38rem' inner_layout='flex flex-col' options='bg-green-500'>
                <h2 className="p-4">Our Work</h2>
                
            </MainCon>
            <MainCon width='46%' height='38rem' inner_layout='grid grid-cols-4 gap-4 place-items-center' options='bg-green-500'>
                {images.map((img, idx) => {
                    return (
                        <img key={idx} src={img} alt={idx.toString()}></img>
                    )
                })}
            </MainCon>
        </>
    )
}

export default Work;