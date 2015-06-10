import urllib
import urllib2
from multiprocessing import Process
import threading

SERVER_HOST="http://172.16.18.138:8080"

OBJECTS_API = "/api/sector/%d/objects"
ROOTS_API = "/api/sector/%d/roots"
COMPANY_API = "/api/sector/%d/company/~~IPP~~/trajectory" #immortal pink productions

def get_objects_roots(sector):
	#~ print sector
	url=SERVER_HOST+OBJECTS_API%sector
	url2 = SERVER_HOST+ROOTS_API % sector
	while True:
		try:
			print sector
			res=urllib2.urlopen(url)
			res2=urllib2.urlopen(url2)
		except Exception:
			continue
		break
	edges = []
	roots = []
	nodes = []
	for line in res2.readlines():
		roots.append(line.strip())
	for line in res.readlines():
		lines=line.strip().split(' ')
		edges.append(lines)
	trying(edges,roots)
	roots=set(roots)
	enough(edges)
	edges3=edges
	#~ print "IT IS ME DIO"
	again=0
	while again==0:
		#~ print "again: "
		#~ print sector
		again=1
		for idx, line in enumerate(edges):
			try:
				if line[-1] in roots:
					Process(target=post_method, args=(sector,line)).start()
					#~ t = threading.Thread(target=post_method, args=(sector,line,1))
					#~ threads.append(t)
					#~ t.start()
				else:
					Process(target=post_method, args=(sector,line)).start()
					#~ t = threading.Thread(target=post_method, args=(sector,line))
					#~ threads.append(t)
					#~ t.start()
				again=0
			except Exception:
				#~ again=0
				continue

def post_method(sector,line,opt=0):
	traj=""
	if opt==0:
		for val in line:
			traj=traj+" "+val
	else:
		a=len(line)
		b=1
		for val in line:
			b+=1
			traj=traj+" "+val
			if b==a:
				break
	values = {'trajectory': traj[1:]}
	url=SERVER_HOST+COMPANY_API%sector#trajectory
	print url
	print values
	while True:
		try:
			data = urllib.urlencode(values)
			print data
			req = urllib2.Request(url, data)
			print req
			response = urllib2.urlopen(req)
			print response
			the_page = response.read()
			print the_page
		except Exception:
			post_method(sector,line,opt)
		break

def trying(edges,roots):
	should_restart=1
	while(should_restart==1):
		should_restart=0
		for idx, val in enumerate(edges):
			if val[0] in roots:
				roots.append(val[1])
				del edges[idx]
				should_restart=1

def enough(edges):
	repeat=1
	#~ print edges[-1]
	#~ print edges[0]
	#~ print edges[1]
	#~ print edges[2]
	while repeat==1:
		repeat=0
		for idx,val in enumerate(edges):
			for idx2,val1 in enumerate(edges):
				try:
					if edges[idx][-1] == edges[idx2][0] and idx != idx2:
						#~ print "--"
						#~ print edges[idx]
						#~ print edges[idx2]
						#~ print idx
						#~ print idx2
						#~ print "-!-"
						#~ print edges[idx]
						del edges[idx][-1]
						#~ print edges[idx]
						#~ print edges[idx2]
						#~ print edges[idx2+1]
						#~ print "-?-"
						value=edges[idx2]
						del edges[idx2]
						if idx2>idx:
							#~ print "ONE"
							for num in value:
								edges[idx].append(num)
							#~ print edges[idx]
							#~ print edges[idx2]
							#~ print "-!?-"
							#~ print edges[idx]
						else:
							#~ print "TWO"
							for num in value:
								edges[idx-1].append(num)
							#~ print edges[idx-1]
							#~ print edges[idx2]
							#~ print "-!?-"
							#~ print edges[idx-1]
						#~ print "\n"
						repeat=1
				except IndexError:
					pass

#get_objects_roots(1)
threads = []
for proc in range(1, 11):
	Process(target=get_objects_roots, args=(proc,)).start()
#a=["148"]
#post_method(2,a,1)
"""
for proc=0;proc<=10;proc+=1:
	p = Process(target=get_objects_roots, args=('proc',))
	p.start()
	p.join()"""
