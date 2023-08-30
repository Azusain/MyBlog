import {useState} from 'react'
 import { backend_addr_4 } from '../BlogsPage';

interface CollapseInterface{
    topic: string;
    columns: Array<string>           // @todo: What's the type of that 'data'?
    isCollapsed: boolean;
    children?: React.ReactNode;
    handler: (data: any) => void
}


// @todo: why is this component rendered twice?
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
                                fetch(
                                    `${backend_addr_4}/columns/${val}`, {
                                        method:"POST",
                                    }
                                )
                                .then((resp) => resp.json())
                                .then((json) => {
                                    props.handler(json)
                                })
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