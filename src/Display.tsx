import React, {useState} from 'react'
import './output.css'
// images
/* codes for importing images should be simplified here!!! */
import img1 from "./img/slide-1.jpg"
import img2 from "./img/slide-2.jpg"
import img3 from "./img/slide-3.jpg"
import img4 from "./img/slide-4.jpg"
import img5 from "./img/slide-5.jpg"


const Display: React.FC = () => {
    // hardcode for animations :XD
    // 15% gap betwwen each img if squeezed
    const init_pos  = ["0%", "20%", "40%", "60%", "80%"]
    const lim_left  = ["0", "15%", "30%", "45%", "60%"]
    const lim_right = ["0", "40%", "55%", "70%", "85%"]
    const [positions, setPositios] = useState(init_pos)
    const images = [img1, img2, img3, img4, img5]
     
    function mouseEnterHandler (event: React.MouseEvent) {
        const elem = event.currentTarget as HTMLElement
        elem.style.filter = "brightness(100%)"
        let curIdx = parseInt(elem.className)
        const new_positions = [...init_pos]
        for (let i = 0; i < 5; i++) {
            new_positions[i] = (i <= curIdx) ? 
                lim_left[i] :lim_right[i]
        }       
        setPositios(new_positions)
    }

    function mouseLeaveHandler(event: React.MouseEvent) {
        const elem = event.currentTarget as HTMLElement
        elem.style.filter = "brightness(60%)"
        setPositios(init_pos)
    }

    return (
        <div className="flex w-full h-[40rem] bg-sky-200 justify-center">
            <div className="flex flex-col w-[46%] h-full bg-slate-500">
                {/* Animation Field */}
                <div className="canvas w-full h-2/3 bg-black relative overflow-hidden">
                    {positions.map((x, index) => {
                        return (
                        <div
                            key={index}
                            style={{
                                top: "10%",
                                left: x,
                                height: "100%",
                                width:"60%",
                                position: "absolute",
                                
                            }}
                        >
                            <img 
                                className = {`${index}`}
                                alt=''
                                style={{
                                    width:"100%", 
                                    height:"90%", 
                                    filter: "brightness(60%)",
                                    cursor: "pointer"
                                }}
                                src={images[index]} 
                                onMouseEnter={mouseEnterHandler}
                                onMouseLeave={mouseLeaveHandler}
                            >
                            </img>  
                        </div>
                        )
                    })}
                </div> {/* Canvas ends */}
                {/* Annotations */}
                <div className="w-full h-1/3 bg-sky-950 flex flex-col">
                    <div className="basis-1/6 bg-orange-300 w-full"></div>
                    <div className="basis-2/3 bg-orange-100 w-full flex flex-row">
                        <div className="basis-1/4  h-full py-10 pl-4"><h2>MOONQUAKE</h2></div>
                        <div className="w-px h-3/4  bg-gray-300 mt-6"></div>
                        <div className="basis-3/4  h-full py-11 pl-8">
                            Coding, Art Design and Audio Engneering. <br></br>
                            Real joy and knowledge here~. Contact us whenever you want
                        </div>
                    </div>
                    <div className="basis-1/6 bg-orange-500 w-full"></div>
                </div>
            </div>
        </div>
    )
}

export default Display;