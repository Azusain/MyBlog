import { useState } from 'react'
import { BlogTopicItemInterface } from './ImageWithDetails';
import { getTopicData } from '../api/passages';

interface CollapseInterface{
    topic: string;
    columns: Array<string>         
    isCollapsed: boolean;
    children?: React.ReactNode;
    handler: (data: BlogTopicItemInterface) => void
}

// @todo: why is this component rendered twice?
// @todo: optimized the codes down below
const Collapse: React.FC<CollapseInterface> = (props) => {
    const [activated, setActivated] = useState(false);

    function expandMenu(){
        setActivated(activated ? false : true)
    }

    return (
        <div className="px-4 hover:cursor-pointer " onClick={expandMenu} >
            <h4 className="font-bold"><u>{props.topic + ' ' + (activated? 'v' : '>')}</u></h4>
            <div className='flex flex-col gap-1 mt-2 '>{
                props.columns.map((val: string, idx:number) => {
                    return (
                        <div 
                            key={idx} 
                            className={(activated? '': 'hidden') + ' collapse-item'}
                            onClick={(e) => {
                                e.stopPropagation()
                                // get api data
                                getTopicData(props.handler, val)
                            }}
                        >
                            {val}
                        </div>
                    )
                })}   
            </div>
        </div>
    )
}

export default Collapse;