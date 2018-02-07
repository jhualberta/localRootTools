from matplotlib import pyplot as plt 

#adjust size
plt.figure(figsize=(6,9))
#labels
labels = [u'part 1',u'part2',u'part3']
#auto percentage
sizes = [60,30,10]
colors = ['red','yellowgreen','lightskyblue']
#explode 
explode = (0.05,0,0)

patches,l_text,p_text = plt.pie(sizes,explode=explode,labels=labels,colors=colors, 
                                labeldistance = 1.1,autopct = '%3.1f%%',
                                shadow = False,startangle = 90,pctdistance = 0.6)
#labeldistance, 1.1x distance from text to far point
#autopctpie, text, font
#shadow
#startangle
#pctdistance
#patches, l_texts, p_texts

#change font size
for t in l_text:
    t.set_size=(30)
for t in p_text:
    t.set_size=(20)
#set x,y equal to make a round
plt.axis('equal')
plt.legend()
plt.show()
