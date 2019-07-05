import requests
from bs4 import BeautifulSoup
import time
import re
import csv

class Spider(object):
    """浙江大学技术交易网爬虫"""
    def __init__(self):

        
        super(Spider, self).__init__()

    def get_url_list(self):
        url_begin = "http://www.zjdxkjw.com/defsub5.asp?ss2=&usid=0&page="
        #http://www.zjdxkjw.com/defsub5.asp
        #http://www.zjdxkjw.com/defsub5.asp?ss2=&usid=0&page=2&Twdk=
        url_end = "&Twdk="
        result = []
        for page in range(1, 12):
            r = requests.get(url_begin + str(page) + url_end).text
            result.append(r)
            time.sleep(0.2)
        return result

    def get_all_urls(self, rs:list):
        all_urls = []
        #print(rs[0])
        for r in rs:
            one_page_urls = []
            #soup = BeautifulSoup(r, ['lxml','xml'])
            #print(soup)
            #one_page_urls = soup.find_all(class_="LL")
            pattern = re.compile(r'\<a href=\"defsub5\.asp\?(.{1,50})\" title=\"')
            one_page_urls = pattern.findall(r)
            #print(one_page_urls)
            #print("length",len(one_page_urls))
            for opu in one_page_urls:
                all_urls.append(opu)

        return all_urls

    def get_info(self, urls:list):
        infos = []
        for u in urls:
            info = {}
            pattern = re.compile(r"^([0-9]{2,4})")
            id = re.findall(pattern=pattern, string=u[3:])[0]

            url = "http://www.zjdxkjw.com/dispkyjg.asp?id=" + id
            # url = "http://www.zjdxkjw.com/dispkyjg.asp?id="+(u[3:7])
            # 有些id是两位或者三位不能这么用
            response = requests.get(url)
            response.encoding = "gbk"
            r = response.text
            #print(r)
            soup = BeautifulSoup(r, 'lxml')
            info_block = soup.find_all(name = "table", attrs = {"width":"94%"})
            #print(info_block)
            name = info_block[0].contents[1].next.contents[3].text.rstrip()

            email = ""
            email_info = info_block[0].contents[7].contents[0].contents[2].contents[0].contents
            if len(email_info) > 0:
                # email可能为空
                #之前这里报异常弄了我很久
                email = email_info[0]


            phone = ""
            phone_info = info_block[0].contents[7].contents[2].contents[2].contents
            if len(phone_info) > 0:
                phone = phone_info[0]

            title = soup.find_all('b')[0].contents[0]

            info["title"] = title
            info["name"] = name
            info["phone"] = phone
            info["email"] = email

            print(info)
            infos.append(info)
            time.sleep(0.2)

        return infos

    def save_to_csv(self, infos, filename):
        with open(filename, 'w', encoding='gbk', newline='') as csvFile:
            fieldnames = ["title", "name", "phone", "email"]
            writer = csv.DictWriter(csvFile, fieldnames=fieldnames)
            writer.writeheader()
            for info in infos:
                writer.writerow(info)

        
if __name__ == '__main__':
    spider = Spider()
    rs = spider.get_url_list()
    urls = spider.get_all_urls(rs)
    spider.get_info(urls)
    #print(urls)
    infos = spider.get_info(urls)
    # for info in infos:
    #     print(info)
    print("开始保存")
    spider.save_to_csv(infos, r"浙江大学技术交易网科研机构.csv")
    print("保存结束")