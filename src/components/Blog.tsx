import { useState } from 'react'
import ImageWithDetails from "./ImageWithDetails";
import MainCon from "./MainCon";
import getColumns from '../api/passages';

// Huge bug here!
const Blog: React.FC = () => {
    const [columnData, setColumnData] = useState<string[]>([])
    var columnsListLocal = sessionStorage.getItem("columns")
    var columnsListLocalObj: Array<string> = [];
    if(!columnsListLocal) {
        getColumns(setColumnData);
    } else {
        columnsListLocalObj = JSON.parse(columnsListLocal)
    }

    return (
        <div className="mt-8 mb-44 w-full">
            <div className="mt-20 mb-8">
                <MainCon width='46%' height='38rem' inner_layout='flex flex-col'>
                    <h2>From Blogs</h2>
                </MainCon>
            </div>
            <MainCon width="46%" height="15rem" inner_layout="flex flex-row gap-4">
                {columnsListLocalObj && (
                    (columnsListLocalObj).map((val: string, idx: number) => {
                        return (<ImageWithDetails key={idx} topic={val}></ImageWithDetails>)
                    })
                )}
            </MainCon>
        </div>
    )
}

export default Blog;