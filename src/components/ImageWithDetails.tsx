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
            <img alt='' src={img0}></img>
            <PassageStatusLine></PassageStatusLine>
            <h4>descriptions...</h4>
            <GuraButton text='Read More'/>
        </div>
    )
}


const BlogItem: React.FC<BlogItemInterface> = (props) => {
    return (
        <div>
            <div className='flex flex-col gap-2'>
                <h3>Linear Algerbra Startup</h3>
                <PassageStatusLine></PassageStatusLine>
                <img 
                    alt='' 
                    src={img0} 
                    className={'p-2 ' + (props.isNews? '' : 'hidden')}
                >
                </img>
                <h4>Linear algebra is central to almost all areas of mathematics. For instance, linear algebra is fundamental in modern presentations of geometry, including for defining basic objects such as lines, planes and rotations</h4>
            </div>
            
            <GuraButton text='Read More'/>
        </div>
    )
}


const PassageStatusLine: React.FC<PassageStatusLineInterface> = (props) => {
    return (
        <div className="flex flex-row w-full justify-between">
            <div className="divide-x flex flex-row gap-2">
                <div>2020-1-21</div>
                <div>Admin</div>
            </div>
            <div>7 Clicks</div>
        </div>
    )
}




export default ImageWithDetails;
export {PassageStatusLine, BlogItem};