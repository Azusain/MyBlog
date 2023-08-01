import {useState} from 'react'
 

interface CollapseInterface{
    topic: string;
    isCollapsed: boolean;
    childern?: React.ReactNode;
}


const Collapse: React.FC<CollapseInterface> = (porps) => {
    
    const [activated, setActivated] = useState(false);
    const list=["Harware", "Circuit Board", "FPGA"]
    
    function expandMenu(){
        setActivated(activated ? false : true)
    }


    return (
        <div className="px-4 hover:cursor-pointer " onClick={expandMenu} >
            <h4 className="font-bold"><u>{porps.topic + ' ' + (activated? 'v' : '>')}</u></h4>
            {list.map((val: string, idx:number) => {
                return (
                    <div key={idx} className={(activated? '': 'hidden' ) + ' pl-6'}>{val}</div>
                )
            })}
        </div>
    )
}

export default Collapse;