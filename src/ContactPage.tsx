
import Footer from "./components/Footer"
import GuraButton from "./components/GuraButton"
import Header from "./components/Header"
import img0 from './img/map.jpg'


const ContactPage: React.FC = () => {
    return (    
        <>
            <Header/>
            <div className="flex w-full h-[40rem]  justify-center bg-slate-800 pt-4">
                <div className="flex flex-row w-[46%] h-full">
                    <div className="basis-2/3 w-full gap-4">
                        <form action="" method="POST">   
                        {/* @todo: request route needed here ~ */}
                            <fieldset>
                            <legend><h3>Contact me</h3></legend>
                            <ul className="flex-col gap-2">
                                <li>
                                    <input className="form-input" type="text" placeholder="Your Name"/>
                                </li>
                                <li>
                                    <input className="form-input" type="email" placeholder="Your Email" multiple/>
                                </li>
                                <li>
                                    <textarea className="block form-input" placeholder="feel free to write down anything you like..."/>
                                </li>
                                <li className="mt-2">
                                    <label>Subscribe to my latest updates</label>
                                    <input className="ml-2" type="checkbox"/>
                                </li>
                                <li><GuraButton text="send"/></li>
                            </ul>
                            </fieldset>
                        </form>
                    </div>
                    
                    <div className="basis-1/3 h-[30rem]">
                        <div className="flex flex-col gap-4">
                            <h3>Contact info</h3>
                            <img alt="" src={img0} className="h-[15rem]"/>
                            <div className="info-text">
                                <div>
                                    <label>Locations:</label>
                                    <h6>Guang Dong, China</h6>
                                </div>
                                <div>
                                    <label>Github:</label>
                                    <h6>Azusain</h6>
                                </div>
                                <div>
                                    <label>Mail:</label> 
                                    <h6>azusaings@gmail.com</h6> 
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <Footer/>
        </>  
    
    )
}

export default ContactPage;