import GuraButton from "./GuraButton";

interface PaginationInterface {
    start: number
}

const Pagination: React.FC<PaginationInterface> = (porps) => {
    let iter = porps.start 
    return (
        <>
            <div className="flex flex-row">
                <GuraButton text="Previous"></GuraButton>
                <div className="flex flex-row place-items-center">
                    {[...Array(5)].map(() => {
                        return(
                            <div
                                className="border-2 border-black w-full p-2 hover:cursor-pointer"
                            >
                                {iter++}
                            </div>
                        )
                    })}
                </div>
                <GuraButton text="Next"></GuraButton>
            </div>
        </>
    )
}

export default Pagination;