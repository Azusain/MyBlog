import React from 'react'
import MainCon from './MainCon'
import '../output.css'

import img1 from "../img/mixing/1.png"


const Work: React.FC = () => {  // @todo: hardcode...
    const images = [img1]
    const names = ["「今日の歌」"]
    const hrefs = ["https://music.163.com/#/song?id=2076320896"]
    return (
        <div className='mb-8'>
            <div className="my-8">
                <MainCon width='46%' height='38rem' inner_layout='flex flex-col'>
                    <h2>Recent Mixing</h2>
                </MainCon>
            </div>
            <MainCon width='46%' height='38rem' inner_layout='grid grid-cols-4 gap-4 place-items-center'>
                {images.map((img, idx) => {
                    return (
                        <div key={idx}>
                            <img src={img} alt={names[idx]} className='shadow-lg mx-works' onClick={() => {
                                window.location.href = hrefs[idx]
                            }}></img>
                            <h6 className='px-20 mt-2'>{names[idx]}</h6>
                        </div>
                    )
                })}
            </MainCon>
        </div>
    )
}

export default Work;