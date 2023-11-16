import MainCon from "./MainCon";

const Footer: React.FC = () => {
    return (
        <div className="mt-8 border-[1px]">
            <MainCon width="full" height="20rem" inner_layout="flex flex-col p-8">
                <div className="h6_black">
                    Designed by azusaing@gmail.com. © Copyright © 2023. 
                    <b> All rights reserved.</b>
                </div>
            </MainCon>
        </div>
    )
}

export default Footer;