import Vue from 'vue';
export default new Vue();
new Vue({
    el: '#app',
    data() {
        return {
            tableData: [],
            fileList: [],
            fileData: [],
            corret: "",
            wrong: "",
            corretList: [],
            wrongList: [],
            form: {
                min: 0,
                max: 10,
                questionNum: 10,
                questionList: [],
                answerList: [],
            }
        }
    },
    beforeCreate() {
        // 读取文件
        FileReader.prototype.reading = function ({ encode } = pms) {
            let bytes = new Uint8Array(this.result);    //无符号整型数组
            let text = new TextDecoder(encode || 'UTF-8').decode(bytes);
            return text;
        };
        /* 重写readAsBinaryString函数 */
        FileReader.prototype.readAsBinaryString = function (f) {
            if (!this.onload)       //如果this未重写onload函数，则创建一个公共处理方式
                this.onload = e => {  //在this.onload函数中，完成公共处理
                    let rs = this.reading();
                    console.log(rs);
                };
            this.readAsArrayBuffer(f);  //内部会回调this.onload方法
        };
    },
    methods: {
        handleRemove(file, fileList) {
            console.log(file, fileList);
        },
        handleExceed(files, fileList) {
            this.$message.warning(`当前限制选择 2 个文件，本次选择了 ${files.length} 个文件，共选择了 ${files.length + fileList.length} 个文件`);
        },
        beforeRemove(file, fileList) {
            return this.$confirm(`确定删除 ${file.name}？`);
        },
        handlePreview(file) {
            console.log(file);
        },


        tableRowClassName({ row, rowIndex }) {//改变表格样式
            if (this.corretList.length != 0 || this.wrongList.length != 0) {
                for (let j = 0; j < this.wrongList.length; j++) {
                    if (rowIndex === (this.wrongList[j] - 1))
                        return 'warning-row'
                }
                for (let i = 0; i < this.corretList.length; i++) {
                    if (rowIndex === (this.corretList[i] - 1))
                        return 'success-row'
                }
            }
            return '';
        },

        createOperationArr(arr1, arr2) {//合并已生成的运算数数组和运算符数组
            let operationArr = []
            let question = ""

            for (let i = 0; i < arr2.length; i++) {
                question += (arr1[i] + arr2[i])
                operationArr.push(arr1[i])
                operationArr.push(arr2[i])
                if (i == (arr2.length - 1)) {
                    question += arr1[(i + 1)]
                    operationArr.push(arr1[(i + 1)])
                }
            }
            return { operationArr, question }
        },

        createQuestionInfo() {//创建一道题目的运算符和运算数，并生
            let operation = [" + ", " − ", " × ", " ÷ ", " / ", " = "]//保存相关运算符
            let operationTime = Math.floor(Math.random() * (3 - 1 + 1) + 1)//运算次数

            //随机生成运算符
            let operationSymbol = []//保存生成的运算符
            for (let k = 0; k < operationTime;) {
                let i = Math.floor(Math.random() * (4 - 0 + 1))

                if (i == 4) {
                    if (operationSymbol.length > 0 && operationSymbol[operationSymbol.length - 1] == operation[i]) {

                    } else {
                        operationSymbol[operationSymbol.length] = operation[i]
                    }
                } else {
                    operationSymbol[operationSymbol.length] = operation[i]
                    k++
                }

            }

            // Math.floor(Math.random()*(n-m+1))+m 取m-n之间的随机数 [m,n]
            //随机生成运算数
            let operationTagNumber = []//保存生成的运算数
            for (let k = 0; k <= operationSymbol.length;) {
                let last = k - 1

                if (k > 0 && (operationSymbol[last] == operation[4] || operationSymbol[last] == operation[3])) {
                    let t = Math.floor(Math.random() * (Number(this.form.max) - Number(this.form.min))) + Number(this.form.min)
                    if (operationSymbol[last] == operation[4] && t != 0 && operationTagNumber[last] <= t) {
                        operationTagNumber[k] = t
                        k++
                    }
                    if (t != 0 && operationSymbol[last] == operation[3]) {
                        operationTagNumber[k] = t
                        k++
                    }
                } else {
                    operationTagNumber[k] = Math.floor(Math.random() * (Number(this.form.max) - Number(this.form.min))) + Number(this.form.min)
                    k++
                }
            }

            let content = this.createOperationArr(operationTagNumber, operationSymbol)
            let operationArr = content.operationArr
            let question = content.question
            question += operation[5]

            operationArr = this.getRPN(operationArr)
            let answer = this.getResult(operationArr)

            return { question, answer }
        },
        createQuestion() {//生成多道题目
            //初始化数据列表
            this.tableData = []
            this.wrongList = []
            this.corretList = []
            this.fileList = []
            this.fileData = []
            this.wrong = ''
            this.corret = ''

            let questionData = []
            for (let i = 0; i < this.form.questionNum;) {
                let content = this.createQuestionInfo()
                let answer = content.answer
                let question = content.question
                let isRepeat = false

                for (let j = 0; j < this.form.questionList.length; j++) {
                    if (this.form.questionList[j] == question) {//检查生成的题目是否重复
                        isRepeat = true
                        break;
                    } else {
                        isRepeat = false
                    }
                }
                if (answer >= 0 && !isRepeat) {
                    this.form.questionList[i] = question
                    this.form.answerList[i] = answer
                    let tag = {}
                    tag.question = question + answer
                    tag.index = i + 1
                    questionData[i] = tag
                    i++
                }
            }
            this.tableData = questionData
        },
        getRPN(arr) {//中缀表达式转后缀表达式
            let symbolPriority = {//确定运算优先级
                " # ": 0,
                " + ": 1,
                " − ": 1,
                " × ": 2,
                " ÷ ": 2,
                " / ": 3
            }
            let operand = []//保存运算数的栈
            let operator = []//保存运算符的栈
            arr.unshift(" # ")//方便进行运算优先级比较

            for (let i = 0; i < arr.length; i++) {
                if (typeof (arr[i]) == "number") {
                    operand.push(arr[i])
                } else {
                    switch (true) {
                        case (arr[i] == ' ( ' || operator.slice(-1)[0] == ' ( '):
                            operator.push(arr[i]);
                            break;
                        case (arr[i] == ' ) '):
                            do {
                                operand.push(operator.pop());
                            } while (operator.slice(-1)[0] != " ( ")
                            operator.pop()
                            break;
                        default:
                            if (operator.length == 0) {
                                operator.push(arr[i]);
                            } else if (symbolPriority[operator.slice(-1)[0]] >= symbolPriority[arr[i]]) {
                                do {
                                    operand.push(operator.pop());
                                } while (symbolPriority[arr[i]] <= symbolPriority[operator[operator.length - 1]])
                                operator.push(arr[i]);
                            } else {
                                operator.push(arr[i]);
                            }
                            break;
                    }
                }
            }
            operator.forEach(function () {
                operand.push(operator.pop());
            });
            operator.pop();//弹出"#"
            return operand;
        },
        getResult(arr) {//获取计算结果
            let result = []//用于保存结果
            let count
            for (let i = 0; i < arr.length; i++) {
                if (typeof (arr[i]) == 'string') {
                    let a = result.pop()
                    let b = result.pop()
                    if (arr[i] == " + ") {
                        count = b + a
                        result.push(count)
                    }
                    if (arr[i] == " − ") {
                        count = b - a
                        result.push(count)
                    }
                    if (arr[i] == " × ") {
                        count = b * a
                        result.push(count)
                    }
                    if (arr[i] == " ÷ ") {
                        count = b / a
                        result.push(count)
                    }
                    if (arr[i] == " / ") {
                        count = b / a
                        result.push(count)
                    }
                } else {
                    result.push(arr[i])
                }
            }
            return result[0]
        },
        downloadQuestion() {//下载题目和答案的txt文件
            let questionContent = ""//题目内容
            let answerContent = ""//答案内容
            if (this.form.questionList.length != 0) {
                let name1 = "Exercises"
                let name2 = "Answers"
                for (let i = 0; i < this.form.questionList.length; i++) {
                    questionContent += (i + 1) + "、" + this.form.questionList[i] + "\n"
                    answerContent += (i + 1) + "、" + this.form.answerList[i] + "\n"
                }
                this.download(name1, questionContent)
                this.download(name2, answerContent)
            } else {
                this.$alert('题目列表为空，请重新生成题目', '', {
                    confirmButtonText: '确定',
                });
            }
        },

        download(filename, text) {//下载TXT文件
            let element = document.createElement('a');
            element.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(text));
            element.setAttribute('download', filename);

            element.style.display = 'none';
            document.body.appendChild(element);

            element.click();

            document.body.removeChild(element);
        },
        beforeUpload(file) {//上传文件
            this.fileList = [file]
            console.log('选择了文件beforeUpload')
            // 读取数据
            this.read(file);
            return false
        },
        read(f) {//解析上传过来的文件
            let rd = new FileReader();
            rd.onload = e => {
                //this.readAsArrayBuffer函数内，会回调this.onload函数。在这里处理结果
                let cont = rd.reading({ encode: 'UTF-8' });
                this.fileData.push(cont)
                let formerData = this.textData;
                this.textData = formerData + "\n" + cont;
            };
            rd.readAsBinaryString(f);

        },
        compareAnswer() {//检查上传过来的题目的答案的正确性并统计相关结果
            let questionContent = []//保存上传过来的题目
            let answerContent = []//保存上传过来的答案
            let corretAnswer = []//保存正确答案
            let corretList = []//保存题目正确答案的序号
            let wrongList = []//保存题目错误答案的序号
            let corret = ""
            let wrong = ""
            //初始化数据列表
            this.form.questionList = []
            this.form.answerList = []

            if (this.fileData.length != 0) {
                for (let i = 0; i < this.fileData.length; i++) {
                    if (this.fileData[i].includes("=")) {
                        questionContent = this.fileData[i].split("\n")
                        for (let k = 0; k < questionContent.length; k++) {
                            for (let n = 0; n < questionContent[i].length; n++) {
                                if (questionContent[k][n] == "、")
                                    questionContent[k] = questionContent[k].substr(n + 1)
                            }
                            if (questionContent[k] == "") {
                                questionContent.pop()
                            } else {
                                corretAnswer[k] = this.getCorrectAnswer(questionContent[k])//获取正确答案
                            }
                        }
                    } else {
                        answerContent = this.fileData[i].split("\n")
                        for (let j = 0; j < answerContent.length; j++) {
                            for (let m = 0; m < answerContent[j].length; m++) {
                                if (answerContent[j][m] == "、")
                                    answerContent[j] = answerContent[j].substr(m + 1)
                            }
                            if (answerContent[j] != "") {
                                answerContent[j] = Number(answerContent[j])
                            } else {
                                answerContent.pop()
                            }
                        }
                    }
                }
                let questionData = []
                for (let n = 0; n < answerContent.length; n++) {
                    if (answerContent[n] == corretAnswer[n]) {
                        corretList.push(n + 1)
                        corret += (n + 1) + ","
                    } else {
                        wrongList.push(n + 1)
                        wrong += (n + 1) + ","
                    }
                    let tag = {}
                    tag.question = questionContent[n] + answerContent[n]
                    tag.index = n + 1
                    questionData[n] = tag
                }
                this.tableData = questionData

                this.corretList = corretList
                this.wrongList = wrongList

                corret = corret.substr(0, corret.length - 1)
                wrong = wrong.substr(0, wrong.length - 1)
                corret = "Correct:" + corretList.length + "（" + corret + "）"
                wrong = "Wrong:" + wrongList.length + "（" + wrong + "）"
                this.corret = corret
                this.wrong = wrong
            } else {
                this.$alert('暂未上传题目，请重新上传题目', '', {
                    confirmButtonText: '确定',
                });
            }
        },
        getCorrectAnswer(str) {//获取正确答案
            let questionArr = str.split(" ")
            questionArr.pop()//弹出最后切到的空格
            for (let i = 0; i < questionArr.length; i++) {
                if (questionArr[i] == '=') {
                    questionArr.splice(i, 1)
                } else {
                    if (questionArr[i] == "/" || isNaN(Number(questionArr[i]))) {
                        questionArr[i] = " " + questionArr[i] + " "
                    } else {
                        questionArr[i] = Number(questionArr[i])
                    }
                }
            }
            questionArr = this.getRPN(questionArr)
            let corretAnswer = this.getResult(questionArr)
            return corretAnswer
        }
    },
})