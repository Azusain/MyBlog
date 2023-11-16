import { BlogItemInterface, BlogTopicItemInterface } from "../components/ImageWithDetails"

var backend_addr_4 = "http://localhost:5001"

async function getColumns(setState: React.Dispatch<React.SetStateAction<string[]>>)
: Promise<any> {
    var tmp_arr: Array<string> = []
    await fetch(
        `${backend_addr_4}/columns`, {
        method: "POST",
    }
    )
    .then((resp) => resp.json())
    .then((json) => {
        for (let i = 0; i < json["columns"].length; ++i) {
            tmp_arr.push(json["columns"][i])
        }
        sessionStorage.setItem("columns", JSON.stringify(json["columns"]))
        setState(tmp_arr)
    })
    return new Promise<Array<string>>((res) => {
        res(tmp_arr)
    })
}

function getTopicData(
    handler: (data: BlogTopicItemInterface) => void,
    val: string,
)
: void {
    fetch(
        `${backend_addr_4}/columns/${val}`, {
            method:"POST",
        }
    )
    .then((resp) => resp.json())
    .then((json) => {
        // structure data
        let psg_arr: Array<BlogItemInterface> = []
        for (let i = 0; i < json.passages.length; ++i) {
            let p: BlogItemInterface = {
                date: json.passages[i].date,
                title: json.passages[i].title,
                brief: json.passages[i].brief,
                img: json.passages[i].img,
                hasImage: true                                            
            }
            psg_arr.push(p) 
        }
        let json_data: BlogTopicItemInterface = {
            brief: json.brief,
            title: json.title,
            passages: psg_arr,
            date: json.date,
            hasImage: true
        }
        sessionStorage.setItem(json_data.title, JSON.stringify(json_data))
        handler(json_data)
    })
}

export default getColumns;
export {getTopicData, backend_addr_4};
