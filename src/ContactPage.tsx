import ContactForm from "./components/ContactForm"
import Footer from "./components/Footer"
import GuraButton from "./components/GuraButton"
import Header from "./components/Header"
import MainCon from "./components/MainCon"
import img0 from './img/blog-1.jpg'


const ContactPage: React.FC = () => {
    return (    
        <>
            <Header/>
            <MainCon width="46%" height="80rem" inner_layout="flex flex-row">
                <div className="basis-2/3 bg-slate-500 w-full gap-4">
                    <div className="flex flex-col gap-4 w-1/2 ">
                        <h3>Contact Me</h3>
                        <input type="text" placeholder="Your Name"></input>
                        <input type="text" placeholder="Phone"></input>
                        <input type="text" placeholder="Email"></input>
                        <textarea></textarea>
                    </div>
                    <div className="flex flex-row gap-4">
                        <GuraButton text="Send"/>
                        <GuraButton text="Clear"/>
                    </div>
                </div>
                
                <div className="basis-1/3 bg-slate-700 h-[30rem]">
                    <h3>Contact Info</h3>
                    <img alt="" src={img0} className="h-[15rem]"/>
                    <h4>Locations: Hong Kong, China</h4>
                    <h4>Github: Azusain</h4>
                    <h4>Mail: azusaings@gmail.com</h4>            
                </div>
 
            </MainCon>
            <Footer/>
        </>  
    
    )
}

export default ContactPage;