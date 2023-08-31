import { BlogItemInterface, BlogTopicItemInterface } from "../components/ImageWithDetails"

var backend_addr_4 = "http://localhost:5001"

function getColumns(setState: React.Dispatch<React.SetStateAction<string[]>>)
: void {
    fetch(
        `${backend_addr_4}/columns`, {
        method: "POST",
    }
    )
    .then((resp) => resp.json())
    .then((json) => {
        var tmp_arr = []
        for (let i = 0; i < json["columns"].length; ++i) {
            tmp_arr.push(json["columns"][i])
        }
        setState(tmp_arr)
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
