import React from 'react'
import GuraButton from './GuraButton';
import img0 from '../img/blog-1.jpg'


interface PassageStatusLineInterface {
    owner?: string;
    date?: string;
    commentsN?: number;
    children?: React.ReactNode;
}

interface BlogItemInterface {
    isNews: boolean
    url?: string
}


const ImageWithDetails: React.FC = () => {
    return (
        <div>
            <h3>Design</h3>
            <img alt='' src={img0} className='shadow-lg'></img>
            <PassageStatusLine></PassageStatusLine>
            <h6>descriptions...</h6>
            <GuraButton text='Read More'/>
        </div>
    )
}


const BlogItem: React.FC<BlogItemInterface> = (props) => {
    return (
        <div>
            <div className='flex flex-col gap-2 p-2'>
                <h3><u>Linear Algerbra Startup</u></h3>

                <PassageStatusLine/>
                
                <img 
                    alt='' 
                    src={img0} 
                    className={props.isNews? '' : 'hidden'}
                >
                </img>
                <h6>Linear algebra is central to almost all areas of mathematics. For instance, linear algebra 
                    is fundamental in modern presentations of geometry, including for defining basic objects such as 
                    lines, planes and rotations</h6>
                <div className={props.isNews? '' : 'hidden'}>
                    <GuraButton text='Read More'/>    
                </div>
            </div>
        </div>
    )
}


const PassageStatusLine: React.FC<PassageStatusLineInterface> = (props) => {
    return (
        <div className="flex flex-row w-full justify-between">
            <div className="flex flex-row gap-2">
                <div>2020-1-21</div>
                <div className='text-gura_main'>Admin</div>
            </div>

        </div>
    )
}




export default ImageWithDetails;
export {PassageStatusLine, BlogItem};